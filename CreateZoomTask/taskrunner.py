  
"""
This is an example showing how to make the scheduler into a remotely accessible service.
It uses RPyC to set up a service through which the scheduler can be made to add, modify and remove
jobs.
To run, first install RPyC using pip. Then change the working directory to the ``rpc`` directory
and run it with ``python -m server``.
"""

import rpyc
from rpyc.utils.server import ThreadedServer

import apscheduler.jobstores.sqlalchemy
from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.triggers.cron import CronTrigger
from apscheduler.triggers.combining import OrTrigger
from apscheduler.executors.pool import ThreadPoolExecutor
from appdata import appdata
import os
from datetime import datetime
from APSched import Task

def serv_joinMeeting(task):
    args=task.args
    print(f'{datetime.now()}: Ran {task.name} ({task.args["confno"]})')
    os.startfile(f'zoommtg://zoom.us/join?{"&".join([arg+"="+args[arg] for arg in args if args[arg]])}')

class SchedulerService(rpyc.Service):
    def exposed_add_job(self, func, *args, **kwargs):
        return scheduler.add_job(serv_joinMeeting, *args, **kwargs)
    
    def exposed_run_job(self, job_id, jobstore='default'):
        return scheduler.modify_job(job_id, jobstore, next_run_time=datetime.now())

    def exposed_modify_job(self, job_id, jobstore='default', **changes):
        return scheduler.modify_job(job_id, jobstore, **changes)

    def exposed_reschedule_job(self, job_id, jobstore='default', trigger=None, **trigger_args):
        return scheduler.reschedule_job(job_id, jobstore, trigger, **trigger_args)

    def exposed_pause_job(self, job_id, jobstore='default'):
        return scheduler.pause_job(job_id, jobstore)

    def exposed_resume_job(self, job_id, jobstore='default'):
        return scheduler.resume_job(job_id, jobstore)

    def exposed_remove_job(self, job_id, jobstore='default'):
        scheduler.remove_job(job_id, jobstore)

    def exposed_get_job(self, job_id):
        return scheduler.get_job(job_id)

    def exposed_get_jobs(self, jobstore='default'):
        return scheduler.get_jobs(jobstore)



if __name__ == '__main__':
    scheduler = BackgroundScheduler()
    url = f'sqlite:///{os.path.join(appdata, "meeting_data.db")}'
    scheduler.add_jobstore('sqlalchemy', url=url)
    scheduler.start()
    print(url)
    protocol_config = {'allow_all_attrs': True, "allow_pickle": True}
    server = ThreadedServer(SchedulerService, port=12345, protocol_config=protocol_config)
    try:
        print('starting')
        server.start()
    except (KeyboardInterrupt, SystemExit):
        pass
    finally:
        scheduler.shutdown()