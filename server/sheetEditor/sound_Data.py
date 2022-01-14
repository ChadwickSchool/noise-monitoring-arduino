
class soundData(object):
    """ A nice place to store data 
    
    """

    def __init__(self, time, avg, max):
        """ Initializes sound data object.

        Parameters
        ----------
        time : str
            the timestamp of the data
        avg : float
            the avrage of sound data
        max : int
            the highst sound data (loudest) 
        
        """
        self.time = time
        self.avg = avg
        self.max = max

    def get_time(self):
        """ Gets the timestamp of the data

        Returns
        -------
        self.time : str
            timestamp of data
        """
        return self.time

    def get_average(self):
        """ Gets the average sound data 

        Returns
        -------
        self.avg : float
            avrage sound data
        """
        return self.avg

    def get_max(self):
        """ Gets the max sound data

        Returns
        -------
        self.,max : int
            max sound data
        """
        return self.max

    def toList(self):
        """ Puts all the data into a list

        Adds Time, Avg, and Max to a list which can be used by other functions to write to spreadsheet. 

        """
        row = []
        row.append("Time")         
        row.append(self.time)
        row.append("Avg")
        row.append(self.avg)
        row.append("Max")
        row.append(self.max)



    
