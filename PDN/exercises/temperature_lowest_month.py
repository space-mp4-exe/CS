from mrjob.job import MRJob
import statistics

class MRAveTemperature(MRJob):

    def mapper(self, _, line):
        fields = line.split(";")
        if fields[0] != "date":
            month = fields[0].split("-")[1]
            temperature = float(fields[1])
            yield (month, temperature)

    def reducer(self, month, list):
        yield (month, statistics.median(list)) 

if __name__ == '__main__':
    MRAveTemperature.run()
