#include "RepoManager.hpp"
#include <sstream>
#include <exception>
#include "dependencies/git2.h"
#include <iostream>


RepoManager::RepoManager() {
    git_libgit2_init();
}


RepoManager::~RepoManager() {
    if (revisionWalker != nullptr) git_revwalk_free(revisionWalker);
    if (repo != nullptr) git_repository_free(repo);
}


bool RepoManager::init(const std::string& path) {
    if (repo != nullptr) {
        git_repository_free(repo);
    }
    
    int error = git_repository_open(&repo, path.c_str());

    if (error < 0) {
        const git_error *e = giterr_last();

        std::stringstream errorStream;

        errorStream << "Error loading git repo. Error: "
            << error 
            << "/"
            << e->klass
            << ": "
            << e->message;

        throw std::runtime_error(errorStream.str());
    }

    return true;
}


unsigned int RepoManager::numberOfRevisions() {
    auto walker = getRevisionWalker();

    // TODO: More error handling

    git_revwalk_sorting(
        revisionWalker,
        GIT_SORT_TOPOLOGICAL | GIT_SORT_TIME
    );

    git_revwalk_push_head(walker);

    git_oid objectId;
    unsigned int revisionCounter = 0;

    while (!git_revwalk_next(&objectId, revisionWalker)) {
        // git_commit* commit;
        // char oidstr[10] = {0};

        // git_commit_lookup(&commit, repo, &objectId);
        // git_oid_tostr(oidstr, 9, &objectId);
        
        // std::cout << git_commit_message(commit) << "\n";

        // git_commit_free(commit);
        revisionCounter++;
    }

    return revisionCounter;
}


git_revwalk* RepoManager::getRevisionWalker() {
    if (revisionWalker == nullptr && repo != nullptr) {
        git_revwalk_new(&revisionWalker, repo);

        // TODO: Handle error code
    }

    return revisionWalker;
}