from django.db import models

# Database Tables


class UserInfo(models.Model):
    uid = models.IntegerField()
    Name = models.CharField(max_length=12)
    Number = models.IntegerField(default=0)
    Class = models.CharField(max_length=6)


class RfidInfo(models.Model):
    uid = models.ForeignKey(UserInfo, on_delete=models.CASCADE)
    Rfid = models.CharField(max_length=16)


class CourseInfo(models.Model):
    cid = models.IntegerField()
    Name = models.CharField(max_length=12)
    Class = models.CharField(max_length=6)
    Begin = models.DateTimeField()
    End = models.DateTimeField()


class AttendInfo(models.Model):
    uid = models.IntegerField()
    cid = models.IntegerField()
    Join = models.DateTimeField()
