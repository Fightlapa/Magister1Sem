from django.db import models
from django.contrib.auth.models import AbstractUser
from django.urls import reverse
from django.core.validators import MaxValueValidator, MinValueValidator

class PGUser(AbstractUser):
    indeks = models.IntegerField(unique=True, validators = [MinValueValidator(100000), MaxValueValidator(1000000)])
    email = models.EmailField(default="NotUsed@wp.pl")
    # is_admin = models.BooleanField(default=False)
    REQUIRED_FIELDS = ['indeks', 'email']
    def __str__(self):
        return self.username
        
    class Meta:
        verbose_name = "Użytkownik PG"
        verbose_name_plural = "Użytkownicy PG"

class ExamTemplate(models.Model):
    teacher = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    name = models.CharField(max_length=100, default="Brak")
    image = models.ImageField(default='default.jpg', upload_to='exam_templates')
    date_modified = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name = "Wzór egzaminu"
        verbose_name_plural = "Wzory egzaminów"

    def __str__(self):
        return self.name

    def get_absolute_url(self):
        return reverse('main-exam-template-detail', kwargs={'pk':self.pk})

class Exam(models.Model):
    student = models.ForeignKey(PGUser, on_delete=models.CASCADE)
    exam_template = models.ForeignKey(ExamTemplate, on_delete=models.CASCADE)
    image = models.ImageField(default='default.jpg', upload_to='written_exams')
    grade = models.IntegerField(default=0)
    date_modified = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name = "Egzamin"
        verbose_name_plural = "Egzaminy"

    def __str__(self):
        return self.student.username + " " + self.exam_template.name

    def get_absolute_url(self):
        return reverse('main-exam-detail', kwargs={'pk':self.pk})

# Create your models here.
