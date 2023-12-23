#include "user.h"

#include <iostream>

bool User::login(const std::string & inputUsername,
  const std::string & inputPassword) {
  if (inputUsername == username && inputPassword == password) {
    isLoggedIn = true;
    std::cout << "Login successful. Welcome, " << username << "!\n";
    return true;
  } else {
    return false;
  }
}

void User::logout() {
  isLoggedIn = false;
  std::cout << "Logout successful. Goodbye, " << username << "!\n";
}
