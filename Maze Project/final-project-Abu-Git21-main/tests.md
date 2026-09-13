Required Test Cases

1. Valid maze file
   Run with maze.txt
   Expected: Maze loads and displays correctly
   Actual: Maze loaded and displayed correctly
   Pass: [x]

2. Missing file
   Rename maze.txt or use a missing filename
   Expected: Error and safe exit
   Actual: Missing file was rejected safely
   Pass: [x]

3. Movement
   Use W/A/S/D
   Expected: Lily moves to valid cells
   Actual: Lily moved correctly
   Pass: [x]

4. Wall collision
   Move toward a wall
   Expected: Lily stays in place
   Actual: Lily stayed in place
   Pass: [x]

5. Boundary collision
   Try to leave the maze
   Expected: Lily stays inside
   Actual: Boundary was rejected
   Pass: [x]

6. Point collection
   Move onto *
   Expected: Score increases once
   Actual: Score increased from 0 to 1
   Pass: [x]

7. Stack push
   Make three moves
   Expected: Three positions are stored
   Actual: Three positions were stored
   Pass: [x]

8. Undo
   Press U after moving
   Expected: Lily returns to the previous position
   Actual: Previous position was restored
   Pass: [x]

9. Empty Undo
   Press U before moving
   Expected: Safe message
   Actual: Printed "Nothing to undo."
   Pass: [x]

10. BFS path
    Press H when a path exists
    Expected: Shortest steps are reported
    Actual: Reported 25 steps
    Pass: [x]

11. BFS no path
    Use blocked_maze.txt
    Expected: Reports no path
    Actual: No path was reported
    Pass: [x]

12. Invalid key
    Press X
    Expected: Program continues
    Actual: Invalid command message displayed
    Pass: [x]

13. Quit
    Press Q
    Expected: Exit and show final score
    Actual: Exited and showed final score
    Pass: [x]

14. Timer
    Allow 60 seconds to pass
    Expected: Program stops and shows final score
    Actual: Verified with a temporary 2-second test
    Pass: [x]

Additional Tests

15. Lowercase movement
    Use lowercase s
    Expected: Command is accepted
    Actual: Lily moved correctly
    Pass: [x]

16. Point collected twice
    Collect the same point twice
    Expected: Score increases once
    Actual: Second collection added no points
    Pass: [x]

17. Invalid maze
    Use an invalid maze
    Expected: Maze is rejected safely
    Actual: Invalid maze was rejected
    Pass: [x]
