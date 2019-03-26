from django import forms
from .models import PGUser, ExamTemplate
from django.contrib.auth.forms import UserCreationForm

class PGUserRegisterForm(UserCreationForm):
    indeks = forms.IntegerField()

    class Meta:
        model = PGUser
        fields = ['username', 'indeks', 'password1', 'password2']



