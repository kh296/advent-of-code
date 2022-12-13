"""
Solutions for Advent of Code 2022 day 13:
https://adventofcode.com/2022/day/13
"""

class Message:
    """
    Class representing a message.

    **Methods:**

    - **__init__()** : Read message lines from file.
    - **part_one()** : Calculate answer to part one of puzzle.
    - **part_two()** : Calculate answer to part two of puzzle.

    """

    def __init__(self, in_path):
        """
        Read message lines from file.
        """

        with open(in_path) as in_file:
            self.message_lines = [eval(line.strip())
                    for line in in_file.readlines() if line.strip()]

    def part_one(self):
        """
        Calculate sum of indices of message lines with elements in right order.
        """
        sum = 0
        for idx in range(len(self.message_lines) // 2):
            sum += (idx + 1) * is_right_order(self.message_lines[2 * idx],
                    self.message_lines[2 * idx + 1])
        return sum

    def part_two(self, divider_packets=[[[2]], [[6]]]):
        """
        Calculate product of indices of lines containing packet dividers,
        after all message lines have been sorted into right order.
        """
        sorted_lines = bubble_sort(self.message_lines + divider_packets)
        indices = [sorted_lines.index(packet) + 1 for packet in divider_packets]
        return indices[0] * indices[1]
    

def bubble_sort(in_list):
    """
    Sort list items so that they are in the right order
    as define by puzzle logic.
    """
    to_sort = len(in_list)
    sorted = False

    slist = list(in_list)
    while not sorted:
        sorted = True
        to_sort -= 1
        for idx in range(to_sort):
            if not is_right_order(slist[idx], slist[idx + 1]):
                slist[idx], slist[idx + 1] = (slist[idx + 1], slist[idx])
                sorted = False

    return slist

def is_right_order(list1, list2):
    """
    Determine if the order list1 followed by list2 is the right order
    for the puzzle logic.
    """

    if not isinstance(list1, list):
        list1 = [list1]
    if not isinstance(list2, list):
        list2 = [list2]

    for idx in range(len(list1)):
        if idx >= len(list2):
            return 0

        if isinstance(list1[idx], int) and isinstance(list2[idx], int):
            if list1[idx] < list2[idx]:
                return 1
            if list1[idx] > list2[idx]:
                return 0
        else:
            right_order = is_right_order(list1[idx], list2[idx])
            if -1 != right_order:
                return right_order

    if len(list1) < len(list2):
        return 1

    return -1

if "__main__" == __name__:
    import sys
    message = Message(sys.argv[1])
    print(f"Part 1: {message.part_one()}")
    print(f"Part 2: {message.part_two()}")
