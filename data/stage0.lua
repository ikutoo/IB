function init()
	setBackground("stage0_bg_00.png")
	beginDialogue("stage0_dialogue_00.lua")
end

function update()
	cnt = getCounter()

	if cnt == 120 then
		displayStageInfo()
	end
end