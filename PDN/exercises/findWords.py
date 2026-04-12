from mrjob.job import MRJob
import re

class MRFindWords(MRJob):
    def mapper(self, _, line):
        match = re.search(r"(_[\w]+_)", line)
        if match:
            word = match.group(1)
            yield (word, line)

    def reducer(self, word, lines):
        for line in lines:
            yield (word, line)

if __name__ == '__main__':
    MRFindWords.run()