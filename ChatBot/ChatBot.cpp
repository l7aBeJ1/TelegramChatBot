#include <stdio.h>
#include <tgbot/tgbot.h>//библиотека для телеграмм бота

int main()
{
    TgBot::Bot bot("5636706261:AAF5qolEMhhyJrdjA55vO_-qg_1LG6FJ8xI");//token bota(выдаётся при создании бота)
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message)
        {
        bot.getApi().sendMessage(message->chat->id, "Hi, " + message->chat->firstName);//Здароваться с человеком по имени
        });
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message)
        {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start"))
        {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);//текст для ответа на непонятный вопрос или команду
        });
    try//try и код ниже не изменяется(шаблон)
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e)
    {
        printf("error: %s\n", e.what());
    }
    return 0;
}