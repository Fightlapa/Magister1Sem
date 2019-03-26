from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from .models import ExamTemplate, PGUser, Exam, Comment
from .forms import PGUserRegisterForm

class CustomUserAdmin(UserAdmin):
    add_form = PGUserRegisterForm
    model = PGUser
    list_display = ['email', 'username',]

admin.site.register(PGUser, CustomUserAdmin)
admin.site.register(ExamTemplate)
admin.site.register(Exam)
admin.site.register(Comment)

# Register your models here.
