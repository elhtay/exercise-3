/*
 * SPDX-FileCopyrightText: Copyright 2023 Arm Limited and/or its affiliates
 * <open-source-office@arm.com> SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*****************************************************************************
 * Includes
 *****************************************************************************/

#include "menu.hpp"

/*****************************************************************************
 * Dishes
 *****************************************************************************/

Dish::Dish(const std::string &_name, unsigned _price)
    : name{_name}, price{_price} {}

Pizza::Pizza(const std::string &name, unsigned price) : Dish(name, price) {}

Burger::Burger(const std::string &name, unsigned _weight, unsigned price)
    : Dish(name, price), weight{_weight} {}

Softdrink::Softdrink(const std::string &name, unsigned _volume, unsigned price)
    : Dish(name, price), volume{_volume} {}

IceCream::IceCream(const std::string &name, unsigned price)
    : Dish(name, price) {}

/*****************************************************************************
 * Order
 *****************************************************************************/

void Order::operator+=(const Order &other)
{
    dishes.insert(dishes.end(), other.dishes.begin(), other.dishes.end());
}

void Order::operator+=(const std::shared_ptr<Dish> &other)
{
    dishes.push_back(other);
}

unsigned Order::getTap() const
{
    unsigned total = 0;
    for (const auto &dish : dishes)
    {
        total += dish->getPrice();
    }
    return total;
}

std::ostream &operator<<(std::ostream &out, const Order &order)
{
    out << "Order with:";
    for (size_t i = 0; i < order.dishes.size(); i++)
    {
        std::shared_ptr<Dish> dish = order.dishes[i];

        if (i > 0)
        {
            out << ",";
        }
        std::string dishName = dish->getName();
        unsigned int price = dish->getPrice();
        out << dishName << " price: " << price;
    }
    return out;
}

/*****************************************************************************
 * Menu
 *****************************************************************************/

Menu::Menu(const Menu &other) : dishes(other.dishes) {}

Menu::Menu(Menu &&other) : dishes(std::move(other.dishes)) {}

Menu::Menu(std::initializer_list<std::shared_ptr<Dish>> l) : dishes(l) {}

void Menu::operator=(const Menu &other)
{
    dishes = other.dishes;
}

void Menu::operator=(Menu &&other)
{
    dishes = std::move(other.dishes);
}

size_t Menu::size() const { return dishes.size(); }

// Helper functions to add dishes to an order

/**
 * @brief Try to find pizza by name and add to order
 *
 * @param order Order to add the pizza to
 * @param item Specification to match
 * @return true if pizza found and added, false otherwise
 */
bool Menu::tryAddToOrder(Order &order, const Pizza &item)
{
    for (size_t i = 0; i < dishes.size(); i++)
    {
        std::shared_ptr<Pizza> pizza = std::dynamic_pointer_cast<Pizza>(dishes[i]);
        if (pizza != nullptr)
        {
            if (pizza->getName() == item.getName())
            {
                order += dishes[i];
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Try to find burger by name (and weight), selecting cheapest match
 *
 * @param order Order to add the burger to
 * @param item  Specification to match
 * @return true if burger found and added, false otherwise
 */
bool Menu::tryAddToOrder(Order &order, const Burger &item)
{
    std::shared_ptr<Burger> burgerPtr = nullptr;

    for (size_t i = 0; i < dishes.size(); i++)
    {
        std::shared_ptr<Burger> burger = std::dynamic_pointer_cast<Burger>(dishes[i]);
        if (burger != nullptr && burger->getName() == item.getName())
        {
            bool weightMatches = (item.getWeight() == 0 || burger->getWeight() == item.getWeight());
            if (weightMatches)
            {
                if (burgerPtr == nullptr || burger->getPrice() < burgerPtr->getPrice())
                {
                    burgerPtr = burger;
                }
            }
        }
    }
    if (burgerPtr == nullptr)
    {
        return false;
    }
    order += burgerPtr;
    return true;
}

/**
 * @brief Try to find softdrink by name (and volume), selecting cheapest match
 *
 * @param order Order to add the softdrink to
 * @param item  Specification to match
 * @return true if softdrink found and added, false otherwise
 */
bool Menu::tryAddToOrder(Order &order, const Softdrink &item)
{
    std::shared_ptr<Softdrink> drinkPtr = nullptr;

    for (size_t i = 0; i < dishes.size(); i++)
    {
        std::shared_ptr<Softdrink> drink = std::dynamic_pointer_cast<Softdrink>(dishes[i]);
        if (drink != nullptr && drink->getName() == item.getName())
        {
            bool volumeMatches = (item.getVolume() == 0 || drink->getVolume() == item.getVolume());
            if (volumeMatches)
            {
                if (drinkPtr == nullptr || drink->getPrice() < drinkPtr->getPrice())
                {
                    drinkPtr = drink;
                }
            }
        }
    }

    if (drinkPtr == nullptr)
    {
        return false;
    }
    order += drinkPtr;
    return true;
}

/**
 * @brief Try to find ice cream by name and add to order
 *
 * @param order Order to add the ice cream to
 * @param item Specification to match
 * @return true if ice cream found and added, false otherwise
 */
bool Menu::tryAddToOrder(Order &order, const IceCream &item)
{
    for (size_t i = 0; i < dishes.size(); i++)
    {
        std::shared_ptr<IceCream> iceCream = std::dynamic_pointer_cast<IceCream>(dishes[i]);
        if (iceCream != nullptr)
        {
            if (iceCream->getName() == item.getName())
            {
                order += dishes[i];
                return true;
            }
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &out, const Menu &menu)
{
    out << "Menu with:";
    for (size_t i = 0; i < menu.dishes.size(); i++)
    {
        if (i > 0)
        {
            out << ",";
        }
        out << menu.dishes[i]->getName() << " price: " << menu.dishes[i]->getPrice();
    }
    return out;
}
