package main

import (
	"log"
	"strings"

	"github.com/gin-gonic/gin"
	"github.com/tarm/serial"
)

func main() {
	config := &serial.Config{
		Name: "/dev/ttyACM1",
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

func splitIntoChunks(s string, chunkSize int) []string {
	var chunks []string
	for i := 0; i < len(s); i += chunkSize {
		end := i + chunkSize
		if end > len(s) {
			end = len(s)
		}

		chunk := s[i:end] + "\n"
		chunks = append(chunks, chunk)
	}
	return chunks
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

	chunks := splitIntoChunks(data.Text, 19)
	for _, chunk := range chunks {
		_, err := s.Write([]byte(chunk))
		if err != nil {
			log.Println(err)
		}
	}

	buf := make([]byte, 128)
	n, err := s.Read((buf))
	if err != nil {
		log.Println(err)
	}

	// completed
	if strings.Contains(string(buf[:n]), "R") || strings.Contains(string(buf[:n]), "j") || strings.Contains(string(buf[:n]), "c") {
		ctx.JSON(204, string(buf[:n]))
	} else {
		ctx.JSON(200, string(buf[:n]))
	}
}
