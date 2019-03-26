from django.db import models
from django.contrib.auth.models import AbstractUser
from django.urls import reverse

class PGUser(AbstractUser):
    indeks = models.IntegerField()
    email = models.EmailField(default="NotUsed@wp.pl")
    # is_admin = models.BooleanField(default=False)
    REQUIRED_FIELDS = ['indeks', 'email']
    def __str__(self):
        return self.username

class ExamTemplate(models.Model):
    teacher = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    name = models.CharField(max_length=100, default="Brak")
    image = models.ImageField(default='default.jpg', upload_to='exam_templates')
    date_modified = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name

    def get_absolute_url(self):
        return reverse('main-exam-detail', kwargs={'pk':self.pk})

class Exam(models.Model):
    student = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    exam_template = models.ForeignKey(ExamTemplate, on_delete=models.CASCADE)
    image = models.ImageField(default='default.jpg', upload_to='written_exams')
    grade = models.IntegerField()

    def __str__(self):
        return f"{self.student} + {self.exam_template}"


class Comment(models.Model):
    user = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    exam = models.ForeignKey(Exam, on_delete=models.CASCADE)
    content = models.CharField(max_length=100, default="Brak")

    def __str__(self):
        return f"{self.user} + {self.content}"
# Create your models here.
