# Structure notes

### Game class

- Updates the window
- Handles input (keyboard)

### Player class

- Creates player
- Moves player
	- Implements gravity
- Player hitbox

Will be used in game class

The players sprites will be implemented in game class
Player is just given its starting position (in constructor)

animations will be made in constructor as well

Public Functions:

- vect getPosition(floor/sides) - gets the new position of a player  (given location of things to hit)
- Animation getCurrentAnimation(state) (given a state (by game class) return the current animation)
- Projectile shoot() - creates a projectile object



### Projectile

- Same as player, but for projectile

Created by player using shoot() function

has 2 animations and a speed

sets animation and sign (direction of speed) based on facingRight (given from player)


## Player

Constructor(init position) * init animations

Vars

- facingRight
- isMoving

- Rectshape   (will be in player, the sprite will be in game)

Private

- isGrounded
- getPos (x and y)

Public

- Animation getCurrentAnimation()
- vect getCurrentPos()
- void update(state) call before two above

- Projectile shoot()
