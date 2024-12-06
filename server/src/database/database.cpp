#include "database.h"

using namespace api::chat;

Database::Database() {

}

Database::~Database() {

}

//<editor-fold desc="User">

std::list<User> Database::get_all_users() {
    return std::list<User>();
}

std::optional<User> Database::get_user_by_id(uint64_t user_id) {
    return std::nullopt;
}

std::optional<User> Database::get_user_by_name(uint64_t user_name) {
    return std::nullopt;
}

bool Database::check_user_password(std::string &user_name, std::string &password) {
    return false;
}

std::list<User> Database::get_user_friends(uint64_t user_id) {
    return std::list<User>();
}

bool Database::make_friend(uint64_t user_id, uint64_t friend_id) {
    return false;
}

bool Database::remove_friend(uint64_t user_id, uint64_t friend_id) {
    return false;
}

//</editor-fold>

//<editor-fold desc="Group">

std::list<Chat> Database::get_all_groups() {
    return std::list<Chat>();
}

std::list<Chat> Database::get_all_groups_for_user(uint64_t user_id) {
    return std::list<Chat>();
}

std::optional<Chat> Database::get_group_by_id(uint64_t group_id) {
    return std::nullopt;
}

bool Database::create_group(std::string &name) {
    return false;
}

bool Database::remove_group(uint64_t group_id) {
    return false;
}

bool Database::add_member(uint64_t group_id, uint64_t user_id) {
    return false;
}

bool Database::remove_member(uint64_t group_id, uint64_t user_id) {
    return false;
}

//</editor-fold>
