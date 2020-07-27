--[[
    ScoreState Class
    Author: Colton Ogden
    cogden@cs50.harvard.edu

    A simple state used to display the player's score before they
    transition back into the play state. Transitioned to from the
    PlayState when they collide with a Pipe.
]]

ScoreState = Class{__includes = BaseState}

--[[
    When we enter the score state, we expect to receive the score
    from the play state so we know what to render to the State.
]]
function ScoreState:enter(params)
    self.score = params.score
end

function ScoreState:update(dt)
    -- go back to play if enter is pressed
    if love.keyboard.wasPressed('enter') or love.keyboard.wasPressed('return') then
        gStateMachine:change('countdown')
    end
end

function ScoreState:render()
    -- simply render the score to the middle of the screen
    love.graphics.setFont(flappyFont)
    love.graphics.printf('Oof! You lost!', 0, 64, VIRTUAL_WIDTH, 'center')

    love.graphics.setFont(mediumFont)
    love.graphics.printf('Score: ' .. tostring(self.score), 0, 100, VIRTUAL_WIDTH, 'center')
    --MEDALS GRAPHIC###############################################################################
    if self.score>=5 and self.score<100 then
        if self.score>=5 and self.score<10 then
            medal=love.graphics.newImage('medal1.png')
        elseif self.score>=10 and self.score<20 then
            medal=love.graphics.newImage('medal2.png')
        elseif self.score>=20 and self.score<30 then
            medal=love.graphics.newImage('medal3.png')
        elseif self.score>=30 and self.score<50 then
            medal=love.graphics.newImage('medal4.png')
        elseif self.score>=50 and self.score<80 then
            medal=love.graphics.newImage('medal5.png')
        elseif self.score>=80 and self.score<100 then
            medal=love.graphics.newImage('medal6.png')
        end
        ximg=medal:getWidth()
        love.graphics.draw(medal,  VIRTUAL_WIDTH/2-ximg/4, 130, 0, 1/2, 1/2)
    elseif self.score>=100 then
        half=VIRTUAL_WIDTH/30
        le=30 --leter 28 but 30
        love.graphics.setFont(flappyFont)
        love.graphics.setColor(255, 0, 0) --red
        love.graphics.printf('E', half-105, 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(255, 128, 0) --orange
        love.graphics.printf('X', half-(le*2.5), 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(255, 255, 51) --yellow
        love.graphics.printf('T', half-(le*1.5), 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(0, 204, 0) --green
        love.graphics.printf('R', half-(le*0.5), 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(153, 204, 255) -- light blue
        love.graphics.printf('E', half+(le*0.5), 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(0, 0, 255) --blue
        love.graphics.printf('M', half+(le*1.5), 140, VIRTUAL_WIDTH, 'center')
        love.graphics.setColor(153, 0, 153) --purple
        love.graphics.printf('E', half+(le*2.5), 140, VIRTUAL_WIDTH, 'center')
        
    else
        love.graphics.setColor(255, 255, 0)
        love.graphics.setFont(flappyFont)
        love.graphics.printf('You can better!', 0, 140, VIRTUAL_WIDTH, 'center')
    end
    -----------------------------------------------------------------------------------------------
    love.graphics.setColor(255, 255, 255)
    love.graphics.setFont(mediumFont)
    love.graphics.printf('Press Enter to Play Again!', 0, 230, VIRTUAL_WIDTH, 'center')
end