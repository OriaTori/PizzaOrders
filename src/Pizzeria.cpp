#include "Pizzeria.h"
#include <iostream>

Pizzeria::Pizzeria(std::string const & name, Pizzas availablePizzas)
    : name_(name)
    , availablePizzas_(availablePizzas)
    , orders_()
{}

std::string Pizzeria::getName()
{
    return name_;
}

bool Pizzeria::validateOrder(Pizzas pizzas)
{
    for (auto pizza : pizzas)
    {
        bool isAvailable = false;
        for (auto availablePizza : availablePizzas_)
        {
            if (pizza->getName() == availablePizza->getName())
            {
                isAvailable = true;
            }
        }
        if (isAvailable == false)
        {
            return false;
        }
    }
    return true;
}

int Pizzeria::makeOrder(Pizzas pizzas)
{
    for (auto const & pizza : pizzas)
    {
        std::cout << "Pizzeria " << name_
                  << ". Making a pizza: " << pizza->getName()
                  << std::endl;
    }
    int orderId = rand() % 100;
    orders_.push_back(std::make_tuple(orderId, pizzas, std::chrono::system_clock::now(), "", 0));
    return orderId;
}

double Pizzeria::calculatePrice(Pizzas pizzas)
{
    double sum = 0.0;
    for (const auto & pizza : pizzas)
    {
        sum += pizza->getPrice();
    }
    return sum;
}

int Pizzeria::setDeliveryAddress(int orderId, std::string deliveryAddress)
{
    int deliveryId;
    for (auto & order : orders_)
    {
        if (std::get<0>(order) == orderId)
        {
            std::get<3>(order) = deliveryAddress;
            deliveryId = rand() % 100;
            std::get<4>(order) = deliveryId;
            std::cout << "Delivery address set to " << std::get<3>(order)
                      << ". DeliveryId = " << std::get<4>(order) << std::endl;
        }
    }
    return deliveryId;
}

bool Pizzeria::checkDeliveryStatus(int deliveryId)
{
    for (auto order : orders_)
    {
        if (std::get<4>(order) == deliveryId)
        {
            auto now = std::chrono::system_clock::now();
            if ((now - std::get<2>(order)) > minutes(7))
            {
                return true;
            }
        }
    }
    return false;
}

bool Pizzeria::isOrderReady(int orderId)
{
    for (auto order : orders_)
    {
        if (std::get<0>(order) == orderId)
        {
            auto now = std::chrono::system_clock::now();
            for (auto pizza : std::get<1>(order))
            {
                if (pizza->getBakingTime() > (now - std::get<2>(order)))
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
