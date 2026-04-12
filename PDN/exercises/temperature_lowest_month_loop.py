from mrjob.job import MRJob

class MRMinTemperature(MRJob):

    def mapper(self, _, line):
        fields = line.split(";")
        if fields[0] != "date":
             month = fields[0].split("-")[1]
             temperature = float(fields[1])
             yield (month, temperature)

    def combiner(self, month, list):
       min_temp = 10000
       for temp in list:
               if temp < min_temp:
                       min_temp = temp
       yield (month, min_temp)

    def reducer(self, month, list):
        min_temp = 10000
        for temp in list:
                if temp < min_temp:
                        min_temp = temp
        yield (month, min_temp)

if __name__ == '__main__':
    MRMinTemperature.run()
