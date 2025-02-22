package main

import (
	"log"

	"github.com/gin-gonic/gin"
	"github.com/tarm/serial"
)

func main() {
	config := &serial.Config{
		Name: "/dev/ttyACM0",
		Baud: 115200,
	}

	s, err := serial.OpenPort(config)
	if err != nil {
		log.Fatal(err)
	}

	log.Println(("Starting server..."))
	router := gin.Default()
	router.POST("/api/new-bobr", func(ctx *gin.Context) { NewBobr(ctx, s) })
	router.Run(":8080")
}

func NewBobr(ctx *gin.Context, s *serial.Port) {
	type params struct {
		Text string `json:"Text"`
	}

	var data params
	if err := ctx.ShouldBindJSON(&data); err != nil {
		log.Println(err)
		ctx.JSON(400, nil)
		return
	}

	data.Text = data.Text + "\n"
	_, err := s.Write([]byte(data.Text))
	if err != nil {
		log.Println(err)
	}

	log.Println(data.Text)
	buf := make([]byte, 128)
	n, err := s.Read((buf))
	if err != nil {
		log.Println(err)
	}

	ctx.JSON(200, string(buf[:n]))
}
