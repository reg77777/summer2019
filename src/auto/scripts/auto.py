#!/usr/bin/env python

import rospy
import smach
import smach_ros

class Init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','pushBtn'])
        self.bt0Mg=False
    def bt0Cb(self,mg):
        self.bt0Mg|=mg.data
    def execute(self,userdata):
        rospy.sleep(0.5)
        rospy.loginfo('Init')
        if self.bt0Mg:
            return 'pushBtn'
        else:
            return 'id'

class R0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.encMg=0
        self.v=100
    def encCb(self,mg):
        self.encMg=mg.data
    def execute(self,userdata):
        rospy.sleep(0.5)
        rospy.loginfo('R0')
        if self.encMg >= self.v:
            return 'id'
        else:
            return 'next'

class Fin(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['toInit'])
    def execute(self,userdata):
        return 'toInit'

def main():
    rospy.init_node('auto')
    sm=smach.StateMachine(outcomes=[])
    with sm:
        smach.StateMachine.add('Init',Init(),
                transitions={'id':'Init','pushBtn':'R0'}) 
        smach.StateMachine.add('R0',R0(),
                transitions={'id':'R0','next':'Fin'})
        smach.StateMachine.add('Fin',Fin(),
                transitions={'toInit':'Init'})
    sis=smach_ros.IntrospectionServer('server_name',sm,'/SM_ROOT')
    sis.start()

    outcome=sm.execute()
    rospy.spin()

if __name__ == '__main__':
    main()
