/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <hidl/MQDescriptor.h>
#include "MessageQueueBase.h"

namespace android {
namespace hardware {

template <typename T, MQFlavor flavor>
struct MessageQueue final : public MessageQueueBase<MQDescriptor, T, flavor> {
    typedef MQDescriptor<T, flavor> Descriptor;
    MessageQueue(const Descriptor& Desc, bool resetPointers = true)
        : MessageQueueBase<MQDescriptor, T, flavor>(Desc, resetPointers) {}
    ~MessageQueue() = default;

    /**
     * This constructor uses Ashmem shared memory to create an FMQ
     * that can contain a maximum of 'numElementsInQueue' elements of type T.
     *
     * @param numElementsInQueue Capacity of the MessageQueue in terms of T.
     * @param configureEventFlagWord Boolean that specifies if memory should
     * also be allocated and mapped for an EventFlag word.
     */
    MessageQueue(size_t numElementsInQueue, bool configureEventFlagWord = false)
        : MessageQueueBase<MQDescriptor, T, flavor>(numElementsInQueue, configureEventFlagWord) {}

  private:
    MessageQueue(const MessageQueue& other) = delete;
    MessageQueue& operator=(const MessageQueue& other) = delete;
    MessageQueue() = delete;
};

}  // namespace hardware
}  // namespace android
