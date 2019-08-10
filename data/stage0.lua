function init()
	setBackground("stage0_bg_00.png")
	beginDialogue("stage0_dialogue_00.lua")
end

function update()
	cnt = getCounter()
	
	if cnt == 240 then displayStageInfo() end
	if cnt == 600 then 
		pEnemy = createEnemy("player_00.png", 0, 0, 64, 96) 
		setPosition(pEnemy, 960, 300)
	end
end