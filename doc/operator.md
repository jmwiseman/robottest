motors 1,2,3,4 drive

 ^    ---
     1   3
     |   |
     2   4
     =====
3 and 4 are reversed

motors 5, (6?) suck up balls?
motor 7 runs track
motor 8 (do high speed motors use the servo ports?do high speed motors have encoders?) runs fly wheel
the gate should probably be actuated by a servo, in which case it would be in port 9, on October 29 we talked about using a solenoid instead, this would use a GP-IO pin instead.

joystic axis for operator mode:
1 2 3 4 5 6 

2 and 4 are meaningless
1+ forward
1- backward
3+ all motors +
3- all motors -


