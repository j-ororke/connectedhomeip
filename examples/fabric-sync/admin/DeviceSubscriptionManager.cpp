/*
 *   Copyright (c) 2024 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "DeviceSubscriptionManager.h"
#include "DeviceManager.h"

#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/InteractionModelEngine.h>
#include <app/server/Server.h>

using namespace ::chip;
using namespace ::chip::app;

namespace admin {

DeviceSubscriptionManager & DeviceSubscriptionManager::Instance()
{
    static DeviceSubscriptionManager instance;
    return instance;
}

CHIP_ERROR DeviceSubscriptionManager::StartSubscription(Controller::DeviceController & controller, ScopedNodeId scopedNodeId)
{
    assertChipStackLockedByCurrentThread();
    auto it = mDeviceSubscriptionMap.find(scopedNodeId);
    VerifyOrReturnError((it == mDeviceSubscriptionMap.end()), CHIP_ERROR_INCORRECT_STATE);

    auto deviceSubscription = std::make_unique<DeviceSubscription>();
    VerifyOrReturnError(deviceSubscription, CHIP_ERROR_NO_MEMORY);
    ReturnErrorOnFailure(deviceSubscription->StartSubscription(
        [this](ScopedNodeId aNodeId) { this->DeviceSubscriptionTerminated(aNodeId); }, controller, scopedNodeId));

    mDeviceSubscriptionMap[scopedNodeId] = std::move(deviceSubscription);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DeviceSubscriptionManager::RemoveSubscription(ScopedNodeId scopedNodeId)
{
    assertChipStackLockedByCurrentThread();
    auto it = mDeviceSubscriptionMap.find(scopedNodeId);
    VerifyOrReturnError((it != mDeviceSubscriptionMap.end()), CHIP_ERROR_NOT_FOUND);
    // We cannot safely erase the DeviceSubscription from mDeviceSubscriptionMap.
    // After calling StopSubscription we expect DeviceSubscription to eventually
    // call the OnDoneCallback we provided in StartSubscription which will call
    // DeviceSubscriptionTerminated where it will be erased from the
    // mDeviceSubscriptionMap.
    it->second->StopSubscription();
    return CHIP_NO_ERROR;
}

void DeviceSubscriptionManager::DeviceSubscriptionTerminated(ScopedNodeId scopedNodeId)
{
    assertChipStackLockedByCurrentThread();
    auto it = mDeviceSubscriptionMap.find(scopedNodeId);
    // DeviceSubscriptionTerminated is a private method that is expected to only
    // be called by DeviceSubscription when it is terminal and is ready to be
    // cleaned up and removed. If it is not mapped that means something has gone
    // really wrong and there is likely a memory leak somewhere.
    VerifyOrDie(it != mDeviceSubscriptionMap.end());
    mDeviceSubscriptionMap.erase(scopedNodeId);
}

} // namespace admin
