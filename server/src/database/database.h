#ifndef SERVER_DATABASE_H
#define SERVER_DATABASE_H

#include <list>
#include <string>
#include <optional>


#include "api_chat.pb.h"

class Database {
public:
    Database();

    ~Database();



    //<editor-fold desc="User">

    std::list<api::chat::User> get_all_users();

    std::optional<api::chat::User> get_user_by_id(uint64_t user_id);

    std::optional<api::chat::User> get_user_by_name(uint64_t user_name);

    bool check_user_password(std::string &user_name, std::string &password);

    std::list<api::chat::User> get_user_friends(uint64_t user_id);

    bool make_friend(uint64_t user_id, uint64_t friend_id);

    bool remove_friend(uint64_t user_id, uint64_t friend_id);

    //</editor-fold>


    //<editor-fold desc="Group">

    std::list<api::chat::Chat> get_all_groups();

    std::list<api::chat::Chat> get_all_groups_for_user(uint64_t user_id);

    std::optional<api::chat::Chat> get_group_by_id(uint64_t group_id);

    bool create_group(std::string &name);

    bool remove_group(uint64_t group_id);

    bool add_member(uint64_t group_id, uint64_t user_id);

    bool remove_member(uint64_t group_id, uint64_t user_id);

    //</editor-fold>

private:

};


#endif //SERVER_DATABASE_H
