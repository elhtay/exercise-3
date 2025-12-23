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

#pragma once

/*****************************************************************************
 * Includes
 *****************************************************************************/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

/*****************************************************************************
 * Dish
 *****************************************************************************/

class Dish {
  public:
    Dish(const std::string &_name, unsigned _price = 0);

  private:
    const std::string name;
    const unsigned price;
};

/*****************************************************************************
 * Pizza
 *****************************************************************************/

class Pizza : public Dish {
  public:
    Pizza(const std::string &name, unsigned price = 0);
};

/*****************************************************************************
 * Burger
 *****************************************************************************/

class Burger : public Dish {
  public:
    Burger(const std::string &name, unsigned _weight = 0, unsigned price = 0);
};

/*****************************************************************************
 * Softdrink
 *****************************************************************************/

class Softdrink : public Dish {
  public:
    Softdrink(const std::string &name, unsigned _volume = 0,
              unsigned price = 0);
};

/*****************************************************************************
 * IceCream
 *****************************************************************************/

class IceCream : public Dish {
  public:
    IceCream(const std::string &name, unsigned price = 0);
};

/*****************************************************************************
 * Order
 *****************************************************************************/

class Order {
  public:
    void operator+=(const Order &other);
    void operator+=(const std::shared_ptr<Dish> &other);
    unsigned getTap() const;

  private:
    std::vector<std::shared_ptr<Dish>> dishes;
};

std::ostream &operator<<(std::ostream &out, const Order &order);

/*****************************************************************************
 * Menu
 *****************************************************************************/

class Menu {
  public:
    Menu(const Menu &other);
    Menu(Menu &&other);
    Menu(std::initializer_list<std::shared_ptr<Dish>> l);

    void operator=(const Menu &other);
    void operator=(Menu &&other);

    size_t size() const;

    template <typename T, typename... Args>
    std::shared_ptr<Order> makeOrder(const T &dish, const Args... _dishes) {
        return nullptr;
    }

  private:
    std::vector<std::shared_ptr<Dish>> dishes;
};

std::ostream &operator<<(std::ostream &out, const Menu &menu);
