#ifndef CHATBOT_H
#define CHATBOT_H
#include "abstract_chatbot.h"

class ChatBot:public AbstractChatBot{
public:
    ChatBot();

    virtual std::string reply(const std::string text);

    // Возвращает для пользователя информацию о чат-боте.
    virtual std::string help() const;

};

#endif // CHATBOT_H
