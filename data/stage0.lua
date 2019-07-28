function init()
	setBackground("stage0_bg_00.png")
	startBgAnm()
	playMusic("stage0_bgm_00.mp3")
	--beginDialogue("stage0_dialogue_00.lua")
end

function update()
	cnt = getCounter()

	if cnt == 240 then
		displayStageInfo()
	end
end