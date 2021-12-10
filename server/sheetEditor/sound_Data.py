
class soundData(object):
    """ A nice place to store data 
    
    """

    def __init__(self, time, avg, max):
        self.time = time
        self.avg = avg
        self.max = max

    def get_time(self):
        return self.time

    def get_average(self):
        return self.avg

    def get_max(self):
        return self.max

    def toList(self):
        row = []
        row.append("Time")         
        row.append(self.time)
        row.append("Avg")
        row.append(self.avg)
        row.append("Max")
        row.append(self.max)



    
