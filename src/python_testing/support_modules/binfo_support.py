#
#    Copyright (c) 2025 Project CHIP Authors
#    All rights reserved.
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

"""
Shared helpers for Basic / Bridged Basic Information python tests.
"""

from __future__ import annotations

from collections.abc import Sequence
from typing import Dict

from matter.testing.runner import TestStep


def plan_step_indices(base_step_order: Sequence[int]) -> Dict[int, int]:
    """Build a mapping from base step number -> harness step index (0..n-1).

    This is used when we are working with a subset of steps but still want to reference
    them using the original test plan numbering.

    Note:
        - Only steps included in base_step_order will be present in the map.
        - For optional steps, use:
              if base in plan_step: self.step(plan_step[base])
    """
    return {base: i for i, base in enumerate(base_step_order)}


def subset_renumbered_test_steps(base_steps: Sequence[TestStep], base_step_order: Sequence[int]) -> list[TestStep]:
    """Create a subset of TestStep objects with renumbered (0..n-1) test_plan_number values.

    This keeps the original step content (description, expectation, etc.) but aligns the
    numbering with what the harness expects after filtering.

    Assumes all base_step_order entries exist in base_steps.
    """
    by_num = {s.test_plan_number: s for s in base_steps}
    out: list[TestStep] = []
    for i, b in enumerate(base_step_order):
        s = by_num[b]
        out.append(TestStep(
            test_plan_number=i,
            description=s.description,
            expectation=s.expectation,
            is_commissioning=s.is_commissioning,
        ))
    return out
