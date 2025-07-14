function sysCall_init() 
    uiCtrl=simGetUIHandle("Kilobot_Controller")
    MsgSensorsHandle=sim.getObjectHandle('KCMsgSensor')

    -- Check if we have more than one controller in the scene:
    i=0
    cnt=0
    while true do
        h=sim.getObjects(i,sim.handle_all)
        if h==-1 then break end
        if simGetObjectCustomData(h,4568)=='kilobotcontroller' then
            cnt=cnt+1
        end
        i=i+1
    end
    if cnt>1 then
        sim.displayDialog('Error',"There is more than one Kilobot controller in the scene.&&nSimulation will not run properly.",sim.dlgstyle_ok,false,nil,{0.8,0.3,0,0,0,0},{0.5,0.25,0,1,1,1})
    end
end
-- Kilobot Controller for Kilobot Model
-- K-Team S.A.
-- 2013.06.24  


function sysCall_cleanup() 
 
end 

function sysCall_actuation() 
    -- get pushed button 
    buttonID=simGetUIEventButton(uiCtrl)
    
    -- test Run button
    if (buttonID==3) then
        tx0=0
        tx1=6
        tx2=1 -- 1=special mode
        sim.sendData(sim.handle_all,0,"Message",sim.packInt32Table({tx0,tx1,tx2}),MsgSensorsHandle,3.00,3.1415,3.1415*2,0.3)
        --sim.addStatusbarMessage(sim.getScriptName(sim.handle_self).." send Run") 
    elseif (buttonID==4) then
    -- test Pause button
         tx0=0
        tx1=4
        tx2=1 -- 1=special mode
        sim.sendData(sim.handle_all,0,"Message",sim.packInt32Table({tx0,tx1,tx2}),MsgSensorsHandle,3.00,3.1415,3.1415*2,0.3)
        --sim.addStatusbarMessage(sim.getScriptName(sim.handle_self).." send Pause") 
    elseif (buttonID==5) then
    -- charge     
        tx0=0
        tx1=7
        tx2=1 -- 1=special mode
        sim.sendData(sim.handle_all,0,"Message",sim.packInt32Table({tx0,tx1,tx2}),MsgSensorsHandle,3.00,3.1415,3.1415*2,0.3)
        --sim.addStatusbarMessage(sim.getScriptName(sim.handle_self).." send Charge") 
    elseif (buttonID==6) then
    -- Bat Volt
        tx0=0
        tx1=5
        tx2=1 -- 1=special mode
        sim.sendData(sim.handle_all,0,"Message",sim.packInt32Table({tx0,tx1,tx2}),MsgSensorsHandle,3.00,3.1415,3.1415*2,0.3)
        --sim.addStatusbarMessage(sim.getScriptName(sim.handle_self).." send Bat Volt") 
    elseif (buttonID==10) then
    -- reset
        tx0=0
        tx1=8
        tx2=1 -- 1=special mode
        sim.sendData(sim.handle_all,0,"Message",sim.packInt32Table({tx0,tx1,tx2}),MsgSensorsHandle,3.00,3.1415,3.1415*2,0.3)
        --sim.addStatusbarMessage(sim.getScriptName(sim.handle_self).." send Reset") 
    end
end