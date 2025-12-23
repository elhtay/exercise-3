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
    : Dish(name, price) {}

Softdrink::Softdrink(const std::string &name, unsigned _volume, unsigned price)
    : Dish(name, price) {}

IceCream::IceCream(const std::string &name, unsigned price)
    : Dish(name, price) {}

/*****************************************************************************
 * Order
 *****************************************************************************/

void Order::operator+=(const Order &other) {
    dishes.insert(dishes.end(), other.dishes.begin(), other.dishes.end());
}

void Order::operator+=(const std::shared_ptr<Dish> &other) {
    dishes.push_back(other);
}

unsigned Order::getTap() const {
    return 0;
}

std::ostream &operator<<(std::ostream &out, const Order &order) { return out; }

/*****************************************************************************
 * Menu
 *****************************************************************************/

Menu::Menu(const Menu &other) {}

Menu::Menu(Menu &&other) {  }

Menu::Menu(std::initializer_list<std::shared_ptr<Dish>> l) {}

void Menu::operator=(const Menu &other) {
}

void Menu::operator=(Menu &&other) {
}

size_t Menu::size() const { return dishes.size(); }

std::ostream &operator<<(std::ostream &out, const Menu &menu) { return out; }
