import argparse
import numpy as np
import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import json

 
# setting up the values for the grid
ON = 255
OFF = 0
vals = [ON, OFF]
updateInterval=50
 
def randomGrid(N,M):
 
    """returns a grid of NxN random values"""
    return np.random.choice(vals, N*M, p=[0.2, 0.8]).reshape(N, M)
def update_grid(frameNum, img, grid, N,M):

	copy_grid=grid.copy()
	for i in range(N):
		for j in range(M):
			total = int((grid[i, (j-1)%M] + grid[i, (j+1)%M] +
                         grid[(i-1)%N, j] + grid[(i+1)%N, j] +
                         grid[(i-1)%N, (j-1)%M] + grid[(i-1)%N, (j+1)%M] +
                         grid[(i+1)%N, (j-1)%M] + grid[(i+1)%N, (j+1)%M])/255)
			if(grid[i,j]==ON):
				if(total<2 or total>3):
					copy_grid[i,j]=OFF
			else:
				if(total==3):
					copy_grid[i,j]=ON
	img.set_data(copy_grid)
	grid[:] = copy_grid[:]
	return img, 


def main():
  
    # set grid size
    
    data = json.load(open('conf.json'))

    N=int(data["rows"])
    M=int(data["cols"])
    
 
    # declare grid
    grid = np.array([])
 
    # check if "glider" demo flag is specified
    grid = randomGrid(N,M)
 
    # set up animation
    fig, ax = plt.subplots()
    img = ax.imshow(grid, interpolation='nearest')
    ani = animation.FuncAnimation(fig, update_grid, fargs=(img, grid, N,M),
                                  frames = 10,
                                  interval=updateInterval,
                                  save_count=50)
 
    
    plt.show()
 
# call main
if __name__ == '__main__':
    main()




