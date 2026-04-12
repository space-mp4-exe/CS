from mrjob.job import MRJob

class MRGenreIndex(MRJob):

    def mapper(self, _, line):
        fields = line.split("\t")
        if fields[0] != "tconst":  # Skip header line
            index = fields[0]
            genres = fields[8]
            if genres != "\\N":   # Skip missing genres
                for genre in genres.split(","):
                    yield (genre.strip(), index)

    def reducer(self, genre, indices):
        yield (genre, sorted(list(indices)))

if __name__ == '__main__':
    MRGenreIndex.run()