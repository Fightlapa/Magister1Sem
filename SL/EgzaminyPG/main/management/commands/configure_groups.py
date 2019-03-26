"""
Create permission groups
Create permissions (read only) to models for a set of groups
"""
import logging

from django.core.management.base import BaseCommand
from django.contrib.auth.models import Group
from django.contrib.auth.models import Permission

GROUPS = ['students', 'teachers']
MODELS = ['exam templates', 'exam', 'comment']

ALL_PERMISSIONS = ['view', 'add', 'delete', 'change']  # For now only view permission by default for all, others include add, delete, change

GROUP_AND_PERMISSIONS = \
{
    'students':
        {
            'exam': ['view'],
            'comment': ['view', 'add', 'change', 'delete']
        },
    'teachers':
        {
            'exam templates': ['view', 'add', 'change', 'delete'],
            'exam': ['view', 'add', 'change', 'delete'],
            'comment': ['view', 'add', 'change', 'delete']
        }
}

class Command(BaseCommand):
    help = 'Creates student and teacher groups and their permissions'

    def handle(self, *args, **options):
        for group, model_and_permissions in GROUP_AND_PERMISSIONS.items():
            new_group, created = Group.objects.get_or_create(name=group)
            for model, permissions in model_and_permissions.items():
                for permission in permissions:
                    name = 'Can {} {}'.format(permission, model)
                    print(f"Creating {name} for {group}")

                    try:
                        model_add_perm = Permission.objects.get(name=name)
                    except Permission.DoesNotExist:
                        logging.warning("Permission not found with name '{}'.".format(name))
                        continue

                    new_group.permissions.add(model_add_perm)

        print("Created default group and permissions.")


# # Permissions section
# students_group, created = Group.objects.get_or_create(name='students')
# # if created:
# #     add_perm = Permission.objects.get(name="Can view template")
# #     students_group.permissions.add(add_perm)
# teachers_group, created = Group.objects.get_or_create(name='teachers')
# if created:
#     view_perm = Permission.objects.get(name="Can view exam templates")
#     add_perm = Permission.objects.get(name="Can add exam templates")
#     delete_perm = Permission.objects.get(name="Can delete exam templates")
#     change_perm = Permission.objects.get(name="Can change exam templates")
#     teachers_group.permissions.add(add_perm, change_perm, delete_perm, view_perm)

