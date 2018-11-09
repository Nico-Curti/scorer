import sys
sys.path.insert(0, '../pyc/')
from Pyscorer import Pyscorer
import numpy as np

if __name__ == '__main__':

  y_true = [2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2] # np.array([2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2], dtype=np.int32)
  y_pred = [0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2] # np.array([0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2], dtype=np.int32)

  scorer = Pyscorer(y_true, y_pred)
  print(scorer)
