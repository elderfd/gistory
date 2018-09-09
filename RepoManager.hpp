#include <string>


struct git_repository;
struct git_revwalk;


class RepoManager {
public:
    RepoManager();
    ~RepoManager();

    bool init(const std::string& path);

    unsigned int numberOfRevisions();

private:
    git_repository* repo = nullptr;
    git_revwalk* revisionWalker = nullptr;

    git_revwalk* getRevisionWalker();
};
