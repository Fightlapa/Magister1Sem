from django.urls import path, re_path
from . import views
from .views import exam_list_view

urlpatterns = [
    path('', views.home, name = 'main-home'),
    path('register', views.register, name = 'main-register'),
    path('exam-templates', views.exam_templates, name = 'main-exam-templates'),
    path('create-exam-template', views.create_exam_template, name = 'main-create-exam-template'),
    re_path(r'^update-exam-template/(?P<exam_id>\d+)/$', views.update_exam_template, name = 'main-update-exam-template'),

]
