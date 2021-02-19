import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router);

import Home from './views/Home.vue';
import Stats from './views/Stats.vue';
import Settings from './views/Settings.vue';

export default new Router({
  linkActiveClass: 'is-active',
  routes: [
    {
      path: '/',
      name: 'Home',
      component: Home
    },
    {
      path: '/statistics',
      name: 'Statistics',
      component: Stats
    },
    {
      path: '/settings',
      name: 'Settings',
      component: Settings
    }
  ]
})

