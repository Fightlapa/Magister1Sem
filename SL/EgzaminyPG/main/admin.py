from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from .models import ExamTemplate, PGUser
from .forms import PGUserRegisterForm

class CustomUserAdmin(UserAdmin):
    add_form = PGUserRegisterForm
    model = PGUser
    list_display = ['email', 'username',]

admin.site.register(PGUser, CustomUserAdmin)
admin.site.register(ExamTemplate)

# Register your models here.
