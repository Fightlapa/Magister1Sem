from django import forms
from .models import PGUser, Exam
from django.contrib.auth.forms import UserCreationForm

class PGUserRegisterForm(UserCreationForm):
    indeks = forms.IntegerField()

    class Meta:
        model = PGUser
        fields = ['username', 'indeks', 'password1', 'password2']

class ExamForm(forms.ModelForm):

    class Meta(object):
        model = Exam
        fields = ['image', 'student', 'grade']
        student = forms.ModelChoiceField(queryset=PGUser.objects.filter(groups__name='students'))

    def __init__(self,*args,**kwargs):
        super (ExamForm,self ).__init__(*args,**kwargs) # populates the post
        self.fields['student'].queryset = PGUser.objects.filter(groups__name='students')

