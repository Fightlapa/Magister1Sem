from django.db import models
from django.contrib.auth.models import AbstractUser
from PIL import Image

class PGUser(AbstractUser):

    indeks = models.IntegerField()
    REQUIRED_FIELDS = ['indeks', 'email']
    def __str__(self):
        return self.username

class ExamTemplates(models.Model):
    teacher = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    name = models.CharField(max_length=100, default="Brak")
    image = models.ImageField(default='default.jpg', upload_to='exam_templates')

    def __str__(self):
        return  self.name


# Create your models here.
