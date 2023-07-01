from setuptools import setup

package_name = 'wkwkyolo'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='cchoirun',
    maintainer_email='niamchoirun020@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        'talker = wkwkyolo.coba:main'
        # 'talker = demo_nodes_py.topics.talker:main'
        # 'listener_qos = demo_nodes_py.topics.listener_qos:main'

    ],
    },
)
