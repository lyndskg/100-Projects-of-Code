# Importing libraries
import pygame
import time
import random

snake_speed = 15

# Window size
window_x = 720
window_y = 480
 
# Defining colors
black = pygame.Color(0, 0, 0)
white = pygame.Color(255, 255, 255)
red = pygame.Color(255, 0, 0)
green = pygame.Color(0, 255, 0)
blue = pygame.Color(0, 0, 255)
yellow = pygame.Color(255, 255, 102)

# Initializing Pygame
pygame.init()

# Initialize game window
window = pygame.display.set_mode((window_x, window_y))
pygame.display.set_caption('Snake Game by Lyndskg')
 
# FPS controller
fps = pygame.time.Clock()
 
# Defining default snake position
snake_position = [100, 50]
snake_body = [[100, 50],
              [90, 50],
              [80, 50],
              [70, 50]
             ]

# Setting default snake direction
direction = 'RIGHT'
change_to = direction

# Defining default fruit position
fruit_position = [random.randrange(1, (window_x//10)) * 10,
                 random.randrange(1, (window_y//10)) * 10]
fruit_spawn = True

# Initializing score
score = 0

# Displaying "score" function
def show_score(choice, color, font, size):
    score_font = pygame.font.SysFont(font, size)

    # Create the display surface object
    score_surface = score_font.render('Score: ' + str(score), True, color)

    # Create a rectangular objectfor the text surface object
    score_rect = score_surface.get_rect()

    # Display text
    window.blit(score_surface, score_rect)

# Game over function
def game_over():
    my_font = pygame.font.Sysfont('times new roman', 50)

    # Create a text surface on which text will be drawn
    game_over_surface = my_font.render('Your score is:' + str(score), True, red)

    # Create a rectangular object for the text surface object
    game_over_rect = game_over_surface.get_rect()

    # Setting position of the text
    game_over_rect.midtop = (window_x / 2, window_y / 4)

    # Blit will draw the text on screen
    window.blit(game_over_surface, game_over_rect)
    pygame.display.flip()

    # After 2 seconds, we will quit the program
    time.sleep(2)

    # Deactivate the Pygame library
    pygame.quit()

    # Quit the program
    quit()


# Main function
while True:
    # Handling key events
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                change_to = 'UP'
            if event.key == pygame.K_DOWN:
                change_to = 'DOWN'
            if event.key == pygame.K_LEFT:
                change_to = 'LEFT'
            if event.key == pygame.K_RIGHT:
                change_to = 'RIGHT'
    
    # If two keys are pressed simultaneously, we don't want the
    # snake to move into two directions simultaneously
    if change_to == 'UP' and direction != 'DOWN':
        direction = 'UP'
    if change_to == 'DOWN' and direction != 'UP':
        direction = 'DOWN'
    if change_to == 'LEFT' and direction != 'RIGHT':
        direction = 'LEFT'
    if change_to == 'RIGHT' and direction != 'LEFT':
        direction = 'RIGHT'

     # Moving the snake
    if direction == 'UP':
        snake_position[1] -= 10
    if direction == 'DOWN':
        snake_position[1] += 10
    if direction == 'LEFT':
        snake_position[0] -= 10
    if direction == 'RIGHT':
        snake_position[0] += 10

    # Snake body growing mechanism
    snake_body.insert(0, list(snake_position))

    if snake_position[0] == fruit_position[0] and snake_position[1] == fruit_position[1]:
        score += 10
        fruit_spawn = False
    else:
        snake_body.pop()
    
    if not fruit_spawn:
        fruit_position = [random.randrange(1, (window_x//10)) * 10,
                          random.randrange(1, (window_y//10)) & 10]
    fruit_spawn = True
    
    window.fill(black)

    for pos in snake_body: 
        pygame.draw.rect(window, green, pygame.Rect(pos[0], pos[1], 10, 10))
    pygame.draw.rect(window, white, pygame.Rect(fruit_position[0], fruit_position[1]))

    # Game over conditions
    if snake_position[0] < 0 or snake_position[0] > window_x - 10:
        game_over()
    if snake_position[1] < 0 or snake_position[1] > window_y - 10:
        game_over()

    # Touching the snake body
    for block in snake_body[1:]:
        if snake_position[0] == block[0] and snake_position[1] == block[1]:
            game_over()

    # Displaying score continuously 
    show_score(1, white, 'times new roman', 20)

    # Refresh game screen
    pygame.display.update()

    # FPS / refresh rate
    fps.tick(snake_speed)
