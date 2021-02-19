<template>
<div class="card">
  <div class="card-content">
    <nav class="navbar" role="navigation" aria-label="main navigation">
      <div class="navbar-brand">
        <router-link class="navbar-item" to="/">
          <img
            src="data:image/png;base64,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"
            alt="ESP-Admin">
        </router-link>

        <a role="button" class="navbar-burger burger" aria-label="menu" :aria-expanded="open" :class="{'is-active': open}" @click.prevent="open = !open">
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
          <span aria-hidden="true"></span>
        </a>
      </div>

      <div class="navbar-menu" :class="{ 'is-active': open }">
        <div class="navbar-end">
          <router-link class="navbar-item" @click.native="open = false" to="/" exact>
            Overview
          </router-link>
          <router-link class="navbar-item" @click.native="open = false" to="/statistics">
            Statistics
          </router-link>
          <router-link class="navbar-item" @click.native="open = false" to="/settings">
            Settings
          </router-link>
        </div>
      </div>
    </nav>
  </div>
</div>
</template>

<script>
  export default {
    props: ['connected', 'stats'],

    data() {
      return {
        open: false,
      }
    },
  }
</script>
