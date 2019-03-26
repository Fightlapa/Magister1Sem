from django.urls import path, re_path
from . import views
from .views import exam_list_view, exam_detail_view, exam_create_view, exam_update_view, exam_delete_view

urlpatterns = [
    path('', views.home, name = 'main-home'),
    path('register/', views.register, name = 'main-register'),
    path('exam-templates/', exam_list_view.as_view(), name = 'main-exam-templates'),
    path('exam-templates/<int:pk>/', exam_detail_view.as_view(), name = 'main-exam-detail'), # pk means primary key
    path('exam-templates/new/', exam_create_view.as_view(), name = 'main-create-exam-template'),
    path('exam-templates/<int:pk>/update/', exam_update_view.as_view(), name = 'main-update-exam-template'),
    path('exam-templates/<int:pk>/delete/', exam_delete_view.as_view(), name = 'main-delete-exam-template'),
    # re_path(r'^update-exam-template/(?P<exam_id>\d+)/$', views.update_exam_template, name = 'main-update-exam-template'),

]
