#ifndef BACKEND_API_H
#define BACKEND_API_H

#include <string>
#include <vector>

namespace BackendAPI {
    // Fetches all issues from the backend (GET /issues)
    std::string get_random_issue();

    // Creates a new issue (POST /issues) with default fields:
    // - status: "pending"
    // - timestamp: current UTC time in ISO 8601 format
    // - upvotes: 0
    std::string createIssue(const std::string& title,
                            const std::string& description,
                            const std::string& location,
                            const std::string& nickname,
                            const std::vector<std::string>& images);

    // Votes for an issue (POST /issues/<issue_id>/vote)
    std::string voteIssue(const std::string& issueID);
}

#endif // BACKEND_API_H
