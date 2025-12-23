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

/*******************************************************************************
 * Includes
 *******************************************************************************/

#include "menu.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <utility>

/*******************************************************************************
 * Unit tests
 *******************************************************************************/

TEST(Restaurant, CopyAndMove) {
    // Initializer list
    Menu menu{std::make_shared<Pizza>("Margarita", 79),
              std::make_shared<Burger>("Burger", 90, 67),
              std::make_shared<Burger>("Burger", 150, 75),
              std::make_shared<Softdrink>("Cola", 33, 25),
              std::make_shared<Softdrink>("Cola", 50, 35),
              std::make_shared<Softdrink>("Cola", 100, 43),
              std::make_shared<IceCream>("Strawberry", 20),
              std::make_shared<IceCream>("Vanilla", 20)};

    // Copy constructor
    Menu menu2{menu};
    ASSERT_EQ(menu.size(), 8);
    ASSERT_EQ(menu2.size(), 8);

    // Move constructor
    Menu menu3{std::move(menu2)};
    ASSERT_EQ(menu2.size(), 0);
    ASSERT_EQ(menu3.size(), 8);

    // Copy operator
    Menu menu4{};
    menu4 = menu3;
    ASSERT_EQ(menu3.size(), 8);
    ASSERT_EQ(menu4.size(), 8);

    // Move operator
    Menu menu5{};
    menu5 = std::move(menu4);
    ASSERT_EQ(menu4.size(), 0);
    ASSERT_EQ(menu5.size(), 8);

    // Test that menu can be printed
    std::cout << "Menu 4: " << menu4 << std::endl;
    std::cout << "Menu 5: " << menu5 << std::endl;
}

TEST(Restaurant, Order) {
    Menu menu{std::make_shared<Pizza>("Margarita", 79),
              std::make_shared<Burger>("Burger", 90, 67),
              std::make_shared<Burger>("Burger", 150, 75),
              std::make_shared<Softdrink>("Cola", 33, 25),
              std::make_shared<Softdrink>("Cola", 50, 35),
              std::make_shared<Softdrink>("Cola", 100, 43),
              std::make_shared<IceCream>("Strawberry", 20),
              std::make_shared<IceCream>("Vanilla", 20)};

    // Create a successful order
    auto order1 = menu.makeOrder(Pizza{"Margarita"}, Softdrink{"Cola", 50});
    ASSERT_NE(order1.get(), nullptr);

    // Create another order, let restaurant select Cola size
    auto order2 = menu.makeOrder(Burger{"Burger", 90}, Softdrink{"Cola"});
    ASSERT_NE(order1.get(), nullptr);

    // Test that orders can be merged
    *order2 += *order1;

    // Test that tap calculation works
    ASSERT_EQ(order2->getTap(), 206);

    // Test that order can be printed
    std::cout << *order2 << std::endl;

    // Fail to create an order
    auto order3 = menu.makeOrder(Pizza{"Calzone"}, Softdrink{"Cola", 33});
    ASSERT_EQ(order3.get(), nullptr);
}
