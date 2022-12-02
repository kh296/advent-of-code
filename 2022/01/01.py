from pathlib import Path
from sys import argv

class Elf():
    def __init__(self, idx=None, cal_count=None):
        self.idx = idx
        self.cal_count = cal_count

    def __repr__(self):
        return f"\nElf {self.idx}: cal_count={self.cal_count}"

class ElfCollection():

    def __init__(self, path="", sort_key=(lambda elf: elf.cal_count)):
        self.path = Path(path)
        self.elves = []

        cal_count = 0
        idx = 1
        with open(path) as infile:
            for line in infile:
                if line.strip():
                    cal_count += int(line)
                else:
                    self.elves.append(Elf(idx, cal_count))
                    cal_count = 0
                    idx += 1

        if cal_count > 0:
            self.elves.append(Elf(idx, cal_count))

        self.elves.sort(key=sort_key, reverse=True)

if "__main__" == __name__:
    elves = ElfCollection(argv[1]).elves
    print(f"\nElf {elves[0].idx} carries {elves[0].cal_count} calories.")
    print(f"\nElves {[elves[i].idx for i in range(3)]} carry "
            f"{sum([elves[i].cal_count for i in range(3)])} calories.")
