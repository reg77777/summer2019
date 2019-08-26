#!/usr/bin/env python

import rospy
import smach
import smach_ros
from geometry_msgs.msg import Twist

class Init(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','pushBtn'])
        self.bt0Mg=True
        self.vMg=Twist()
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def bt0Cb(self,mg):
        self.bt0Mg|=mg.data
    def execute(self,userdata):
        rospy.sleep(4)
        self.vPb.publish(self.vMg)
        if self.bt0Mg:
            return 'pushBtn'
        else:
            return 'id'

class R(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.Sb=rospy.Subscriber('enc0',Int32,self.Cb);
        self.vMg=Twist()
        self.vMg.linear.x=200;
        self.vPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def RCb(self,mg):
        self.c=mg.data
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        return 'next'

class UR(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.x=200;
        self.vMg.linear.y=200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class U(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.y=200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class UL(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.x=-200;
        self.vMg.linear.y=200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class L(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.x=-200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class DL(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.x=-200;
        self.vMg.linear.y=-200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class D(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.y=-200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class DR(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['next'])
        self.time=2
        self.vMg=Twist()
        self.vMg.linear.x=200;
        self.vMg.linear.y=-200;
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'next'

class Fin(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id'])
        self.time=2
        self.vMg=Twist()
        self.vPb=rospy.Publisher('cmd_vel',Twist,queue_size=10)
    def execute(self,userdata):
        self.vPb.publish(self.vMg)
        rospy.sleep(self.time)
        return 'id'

def main():
    rospy.init_node('auto')
    sm=smach.StateMachine(outcomes=[])
    with sm:
        smach.StateMachine.add('Init',Init(),
                transitions={'id':'Init','pushBtn':'R'})
        smach.StateMachine.add('R',R(),
                transitions={'next':'UR'})
        smach.StateMachine.add('UR',UR(),
                transitions={'next':'U'})
        smach.StateMachine.add('U',U(),
                transitions={'next':'UL'})
        smach.StateMachine.add('UL',UL(),
                transitions={'next':'L'})
        smach.StateMachine.add('L',L(),
                transitions={'next':'DL'})
        smach.StateMachine.add('DL',DL(),
                transitions={'next':'D'})
        smach.StateMachine.add('D',D(),
                transitions={'next':'DR'})
        smach.StateMachine.add('DR',DR(),
                transitions={'next':'Fin'})
        smach.StateMachine.add('Fin',Fin(),
                transitions={'id':'Fin'})

        outcome=sm.execute()
        rospy.spin()

if __name__ == '__main__':
    main()
