//
// Created by Paul on 2022/01/01.
//

#ifndef TREE_FAILUREMODES_H
#define TREE_FAILUREMODES_H


#include <string>

class FailureModes {
private:
    std::string name;
    std::string description;
    std::string tag;

public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getDescription() const;

    void setDescription(const std::string &description);

    const std::string &getTag() const;

    void setTag(const std::string &tag);


};


#endif //TREE_FAILUREMODES_H
