from mrjob.job import MRJob
from mrjob.step import MRStep
import re

class LongestWordPerLetter(MRJob):

    def steps(self):
        return [
            MRStep(mapper=self.mapper_extract_words,
                   reducer=self.reducer_find_longest),
            MRStep(reducer=self.reducer_collect_longest)
        ]

    # Extract words and emit (first_letter, word).
    def mapper_extract_words(self, _, line):
        words = re.findall(r"[a-zA-Z]+", line)
        for word in words:
            letter = word[0].lower()
            yield letter, word.lower()

    # Find the max length and collect all words matching it.
    # Emits (letter, (max_length, [word1, word2, ...])).
    def reducer_find_longest(self, letter, words):
        max_len = 0
        longest_words = []

        for word in words:
            word_len = len(word)
            if word_len > max_len:
                max_len = word_len
                longest_words = [word]
            elif word_len == max_len:
                if word not in longest_words:
                    longest_words.append(word)

        yield letter, (max_len, longest_words)

    # Handles the case where the same letter's data was split across multiple reducer_find_longest calls. Merges and finds the true longest.
    def reducer_collect_longest(self, letter, length_word_pairs):
        max_len = 0
        longest_words = []

        for length, words in length_word_pairs:
            if length > max_len:
                max_len = length
                longest_words = words
            elif length == max_len:
                for word in words:
                    if word not in longest_words:
                        longest_words.append(word)

        yield letter, (sorted(longest_words))


if __name__ == '__main__':
    LongestWordPerLetter.run()