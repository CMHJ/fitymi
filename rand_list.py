#!/usr/bin/env python3
# Stolen from https://stackoverflow.com/questions/3589214/generate-random-numbers-summing-to-a-predefined-value
import random

def constrained_sum_sample_pos(n, total):
    """Return a randomly chosen list of n positive integers summing to total.
    Each such list is equally likely to occur."""

    dividers = sorted(random.sample(range(1, total), n - 1))
    print(dividers)
    print([total])
    print(dividers + [total])
    print([0])
    print(dividers)
    print([0] + dividers)
    return [a - b for a, b in zip(dividers + [total], [0] + dividers)]

print(constrained_sum_sample_pos(4, 40))
