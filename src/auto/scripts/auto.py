#!/usr/bin/env python

import rospy
import smach
import smach_ros
from geometry_msgs.msg import Twist
from std_msgs.msg import Int16

class INIT(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','pushBtn'])
        self.bt0Mg=True
        self.encResetMg=Int16()
        self.encResetPb=rospy.Publisher('encReset',Int16,queue_size=10)
    def bt0Cb(self,mg):
        self.bt0Mg|=mg.data
    def execute(self,userdata):
        self.encResetPb.publish(self.encResetMg)
        rospy.sleep(4)
        if self.bt0Mg:
            return 'pushBtn'
        else:
            return 'id'

class R0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('R0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class STOP0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        #rospy.sleep(5)
        return 'next'

class RELEASE(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
    def execute(self,userdata):
        #rospy.sleep(5)
        return 'next'

class L0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('L0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'
    
class LU0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('LU0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class U0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('U0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class RU0(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
        ds=rospy.get_param('RU0d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class U1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('U1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class LU1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('LU1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class U2(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('U2d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class R1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('R1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class STOP1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class L1(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('L1d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class ROTATE(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('ROTATEd')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

class U3(smach.State):
    def __init__(self):
        smach.State.__init__(self,outcomes=['id','next'])
        self.mMg=Twist()
        ds=rospy.get_param('U3d')
        self.mMg.linear.x=ds[0]
        self.mMg.linear.y=ds[1]
        self.mMg.angular.z=ds[2]
        self.mPb=rospy.Publisher('cmd_move',Twist,queue_size=10)
    def execute(self,userdata):
        self.mPb.publish(self.mMg)
        rospy.sleep(5)
        return 'next'

def main():
    rospy.init_node('auto')
    sm=smach.StateMachine(outcomes=[])
    with sm:
        smach.StateMachine.add('INIT',INIT(),
                transitions={'id':'INIT','pushBtn':'R0'})
        smach.StateMachine.add('R0',R0(),
                transitions={'id':'R0','next':'STOP0'})
        smach.StateMachine.add('STOP0',STOP0(),
                transitions={'id':'STOP0','next':'RELEASE'})
        smach.StateMachine.add('RELEASE',RELEASE(),
                transitions={'id':'RELEASE','next':'L0'})
        smach.StateMachine.add('L0',L0(),
                transitions={'id':'L0','next':'LU0'})
        smach.StateMachine.add('LU0',LU0(),
                transitions={'id':'LU0','next':'U0'})
        smach.StateMachine.add('U0',U0(),
                transitions={'id':'U0','next':'RU0'})
        smach.StateMachine.add('RU0',RU0(),
                transitions={'id':'RU0','next':'U1'})
        smach.StateMachine.add('U1',U1(),
                transitions={'id':'U1','next':'LU1'})
        smach.StateMachine.add('LU1',LU1(),
                transitions={'id':'LU1','next':'U2'})
        smach.StateMachine.add('U2',U2(),
                transitions={'id':'U2','next':'R1'})
        smach.StateMachine.add('R1',R1(),
                transitions={'id':'R1','next':'STOP1'})
        smach.StateMachine.add('STOP1',STOP1(),
                transitions={'id':'STOP1','next':'L1'})
        smach.StateMachine.add('L1',L1(),
                transitions={'id':'L1','next':'ROTATE'})
        smach.StateMachine.add('ROTATE',ROTATE(),
                transitions={'id':'ROTATE','next':'U3'})
        smach.StateMachine.add('U3',U3(),
                transitions={'id':'U3','next':'INIT'})

        outcome=sm.execute()
        rospy.spin()

if __name__ == '__main__':
            main()
