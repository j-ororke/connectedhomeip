/**
 *    Copyright (c) 2024 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#import <Foundation/Foundation.h>
#import <Matter/MTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

MTR_AVAILABLE(ios(18.3), macos(15.3), watchos(11.3), tvos(18.3))
@interface MTRAttributeValueWaiter : NSObject
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Cancel the wait for the set of attribute path/value pairs represented by this
 * MTRAttributeValueWaiter.  If the completion has not been called yet, it will
 * becalled with MTRErrorCodeCancelled.
 */
- (void)cancel;

@property (readonly, nonatomic) NSUUID * UUID MTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

NS_ASSUME_NONNULL_END
